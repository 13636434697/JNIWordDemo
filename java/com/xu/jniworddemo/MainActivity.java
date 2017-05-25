package com.xu.jniworddemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
/*
* 字符串加密的demo
* */
public class MainActivity extends AppCompatActivity {
    static{
        System.loadLibrary("encode");
    }
    EditText et ;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        et = (EditText) findViewById(R.id.et_text);
    }

    //加密的方法
    public void encode(View v){
        //获取edittext的文字
        String word = et.getText().toString();
        //传递c加密处理
        word = encodeInC(word);
        //把处理后的结果显示到edittext上
        et.setText(word);
    }

    //解密的方法
    public void decode(View v){
        //获取edittext的文字
        String word = et.getText().toString();
        //传递c加密处理
        word = decodeInC(word);
        //把处理后的结果显示到edittext上
        et.setText(word);

    }

    public native String encodeInC(String word);

    public native String decodeInC(String word);
}
