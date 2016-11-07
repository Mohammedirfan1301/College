package epic.quickflash;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

// Imports for camera LED
import android.hardware.Camera;
import android.hardware.Camera.Parameters;

import android.content.pm.PackageManager;
import android.view.View;
import android.widget.Toast;
import android.widget.ToggleButton;

public class MainActivity extends ActionBarActivity {

    public static Camera cam = null;        // has to be static, otherwise onDestroy() destroys it
    boolean isLightOn = false;
    Parameters p = cam.getParameters();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        cam = Camera.open();
        p = cam.getParameters();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    // Make sure to release the camera when the app stops.
    @Override
    protected void onStop() {
        super.onStop();

        if (cam != null) {
            cam.release();
        }
    }

    public void onToggleClicked(View view) {

        if(isLightOn) {
            // Turn the flashlight on.
            flashLightOn(view);
        } else {
            // The the flashlight off.
            flashLightOff(view);
        }
    }

    public void flashLightOn(View view) {
        p.setFlashMode(Parameters.FLASH_MODE_TORCH);
        cam.setParameters(p);
        cam.startPreview();
        isLightOn = true;
    }

    public void flashLightOff(View view) {
        p.setFlashMode(Parameters.FLASH_MODE_OFF);
        cam.setParameters(p);
        cam.stopPreview();
        isLightOn = false;
    }

}
