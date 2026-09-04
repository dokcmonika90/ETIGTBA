package com.eigtba.recompiler

import android.app.Activity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.TextView
import android.widget.LinearLayout

class MainActivity : Activity() {
    private external fun nativeVersion(): String
    private external fun nativeLoad(bytes: ByteArray): Boolean
    private external fun nativeReset()
    companion object { init { System.loadLibrary("retro_recompiler") } }

    override fun onCreate(state: Bundle?) { super.onCreate(state)
        val root = LinearLayout(this).apply { orientation = LinearLayout.VERTICAL; setPadding(32,32,32,32) }
        val title = TextView(this).apply { text = "Retro Recompiler • Android\n" + nativeVersion(); textSize = 24f }
        val status = TextView(this).apply { text = "Select a legally dumped NES ROM to begin."; textSize = 16f; setPadding(0,24,0,24) }
        val reset = Button(this).apply { text = "Reset CPU"; setOnClickListener { nativeReset(); status.text = "CPU reset." } }
        root.addView(title); root.addView(status); root.addView(reset); setContentView(root)
    }
}
