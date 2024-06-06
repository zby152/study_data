package an.droid.j;

import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

/* loaded from: classes.dex */
public class MainActivity extends AppCompatActivity {
    long df_all;
    long t;
    long t1;
    long t2;
    int zygote = 1357024680;

    public native String j(int i);

    public native int p(int i);

    /* JADX INFO: Access modifiers changed from: protected */
    @Override // android.support.v7.app.AppCompatActivity, android.support.v4.app.FragmentActivity, android.support.v4.app.SupportActivity, android.app.Activity
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        setContentView(R.layout.activity_main);
        final TextView textView = (TextView) findViewById(R.id.tv1);
        final Handler handler = new Handler();
        final Runnable runnable = new Runnable() { // from class: an.droid.j.MainActivity.1
            @Override // java.lang.Runnable
            public void run() {
                MainActivity.this.t2 = System.currentTimeMillis();
                long j = MainActivity.this.t2 - MainActivity.this.t1;
                MainActivity mainActivity = MainActivity.this;
                mainActivity.df_all = mainActivity.t2 - MainActivity.this.t;
                if (j > 100) {
                    MainActivity.this.t1 += 100;
                    MainActivity mainActivity2 = MainActivity.this;
                    mainActivity2.zygote = mainActivity2.p(mainActivity2.zygote);
                    textView.setText(String.format("Time:%.1f", Double.valueOf(Math.floor(MainActivity.this.df_all / 100) / 10.0d)));
                }
                handler.postDelayed(this, 30L);
            }
        };
        ((Button) findViewById(R.id.bt1)).setOnClickListener(new View.OnClickListener() { // from class: an.droid.j.MainActivity.2
            @Override // android.view.View.OnClickListener
            public void onClick(View view) {
                MainActivity.this.t = System.currentTimeMillis();
                MainActivity mainActivity = MainActivity.this;
                mainActivity.t1 = mainActivity.t;
                handler.postDelayed(runnable, 0L);
            }
        });
        ((Button) findViewById(R.id.bt2)).setOnClickListener(new View.OnClickListener() { // from class: an.droid.j.MainActivity.3
            @Override // android.view.View.OnClickListener
            public void onClick(View view) {
                handler.removeCallbacks(runnable);
                if (MainActivity.this.df_all / 100 == 99999) {
                    TextView textView2 = textView;
                    StringBuilder sb = new StringBuilder();
                    sb.append("flag{");
                    MainActivity mainActivity = MainActivity.this;
                    sb.append(mainActivity.j(mainActivity.zygote));
                    sb.append("}");
                    textView2.setText(sb.toString());
                } else if (MainActivity.this.df_all / 100 < 9999) {
                    textView.setText("too soon");
                } else {
                    textView.setText("too late");
                }
            }
        });
    }

    static {
        System.loadLibrary("j");
    }
}