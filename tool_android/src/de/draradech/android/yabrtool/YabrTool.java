package de.draradech.android.yabrtool;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Timer;
import java.util.TimerTask;
import java.util.UUID;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Button;

public class YabrTool extends Activity implements SensorEventListener
{
   private SensorManager mSensorManager;
   private WakeLock mWakeLock;
   private TextView mTextView;
   private Button mConnectButton;
   private Button mModeButton;
   private Timer mTimer;
   private TimerTask mTimerTask;
   private BluetoothSocket mBluetoothSocket;
   private Runnable mRunnable;
   private OutputStream mOut;
   private int mCount = 0;
   private float mV1, mV2, mV3;
   private boolean mAccEnabled;
   private boolean mConnected;

   @Override
   public void onCreate(Bundle savedInstanceState)
   {
      super.onCreate(savedInstanceState);
      mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
      mWakeLock = ((PowerManager) getSystemService(POWER_SERVICE)).newWakeLock(PowerManager.SCREEN_BRIGHT_WAKE_LOCK, getClass().getName());
      setContentView(R.layout.main);
      mTextView = (TextView) findViewById(R.id.text);
      mConnectButton = (Button) findViewById(R.id.connect_button);
      mModeButton = (Button) findViewById(R.id.mode_button);
      mTimer = new Timer();
      try
      {
         mBluetoothSocket = BluetoothAdapter.getDefaultAdapter().getRemoteDevice("00:06:66:02:CE:27").createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
         Log.i("YabrTool", "socket created");
      }
      catch(IOException ioe)
      {
         Log.w("YabrTool", "socket creation failed: " + ioe.toString());
      }
      mRunnable = new Runnable(){@Override public void run(){tick();}};
   }

   @Override
   protected void onResume()
   {
      super.onResume();
      mWakeLock.acquire();
      mSensorManager.registerListener(this, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_GAME);
      mTimerTask = new TimerTask(){@Override public void run(){runOnUiThread(mRunnable);}};
      mTimer.scheduleAtFixedRate(mTimerTask, 0, 100);
   }

   @Override
   protected void onPause()
   {
      super.onPause();
      mSensorManager.unregisterListener(this);
      mWakeLock.release();
      mTimerTask.cancel();
   }

   @Override
   public void onSensorChanged(SensorEvent event)
   {
      mV1 = event.values[0];
      mV2 = event.values[1];
      mV3 = event.values[2];
   }

   @Override
   public void onAccuracyChanged(Sensor sensor, int accuracy)
   {
   }

   private void tick()
   {
      mCount++;
      mTextView.setText(String.format("%d\n%.1f\n%.1f\n%.1f\n", mCount, mV1, mV2, mV3));
      if(mAccEnabled)
      {
         try
         {
            mOut.write('{');
            mOut.write('f');
            mOut.write((int)(mV3*10));
            mOut.write('}');
            mOut.write('{');
            mOut.write('l');
            int rl = (int)(mV2*20);
            mOut.write(rl<-126?-126:rl>126?126:rl);
            mOut.write('}');
         }
         catch(IOException ioe)
         {
            Log.w("YabrTool", "write failed: " + ioe.toString());
         }
      }
   }

   public void connect(View v)
   {
      if(mConnected)
      {
         try
         {
            mBluetoothSocket.close();
            mAccEnabled = false;
            mModeButton.setEnabled(false);
            mModeButton.setText("Enable Acc");
            mConnectButton.setText("Connect");
            mConnected = false;
            Log.i("YabrTool", "disconnected");
         }
         catch(IOException ioe)
         {
            Log.w("YabrTool", "disconnect failed: " + ioe.toString());
         }
      }
      else
      {
         try
         {
            mBluetoothSocket.connect();
            mConnectButton.setText("Disconnect");
            Log.i("YabrTool", "connected!");
            mModeButton.setEnabled(true);
            mOut = mBluetoothSocket.getOutputStream();
            mOut.write('{');
            mOut.write('s');
            mOut.write('}');
            mConnected = true;
            Log.i("YabrTool", "silence requested");
         }
         catch(IOException ioe)
         {
            Log.w("YabrTool", "connect failed: " + ioe.toString());
         }
      }
   }

   public void mode(View v)
   {
      if(mAccEnabled)
      {
         mAccEnabled = false;
         mModeButton.setText("Enable Acc");
      }
      else
      {
         mAccEnabled  = true;
         mModeButton.setText("Disable Acc");
      }
   }
}
