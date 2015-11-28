#include "com_example_hp_myfirstapp_MyActivity.h"

JNIEXPORT jstring JNICALL Java_com_example_hp_myfirstapp_MyActivity_HelloJNI
        (JNIEnv *env, jobject obj)
{
    (*env)->NewStringUTF(env, "Hello from jni");
}
