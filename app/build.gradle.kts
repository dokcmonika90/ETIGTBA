plugins { id("com.android.application"); id("org.jetbrains.kotlin.android") }

android { namespace = "com.eigtba.recompiler"; compileSdk = 35
    defaultConfig { applicationId = "com.eigtba.recompiler"; minSdk = 26; targetSdk = 35; versionCode = 1; versionName = "0.1.0" }
    buildFeatures { viewBinding = true }
    externalNativeBuild { cmake { path = file("src/main/cpp/CMakeLists.txt"); version = "3.30.5" } }
}

dependencies { implementation("androidx.core:core-ktx:1.15.0"); implementation("androidx.appcompat:appcompat:1.7.0"); implementation("com.google.android.material:material:1.12.0") }
