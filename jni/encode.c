#include <jni.h>
#include <stdlib.h>

/**
 * 把一个jstring转换成一个c语言的char* 类型.
 */
char* _JString2CStr(JNIEnv* env, jstring jstr) {
	 char* rtn = NULL;
	 jclass clsstring = (*env)->FindClass(env, "java/lang/String");
	 jstring strencode = (*env)->NewStringUTF(env,"GB2312");
	 jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
	 jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid, strencode); // String .getByte("GB2312");
	 jsize alen = (*env)->GetArrayLength(env, barr);
	 jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
	 if(alen > 0) {
		rtn = (char*)malloc(alen+1); //"\0"
		memcpy(rtn, ba, alen);
		rtn[alen]=0;
	 }
	 (*env)->ReleaseByteArrayElements(env, barr, ba,0);
	 return rtn;
}
/*这里是加密的处理，这里是加
 * Class:     com_xu_jniworddemo_MainActivity
 * Method:    encodeInC
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
 //拿到字符串要加密必须要遍历一下，每一个字符加一或者加2，在转化成jstring返回
JNIEXPORT jstring JNICALL Java_com_xu_jniworddemo_MainActivity_encodeInC (JNIEnv * env, jobject obj, jstring jstr){
  	//把jstring类型字符串转化成 c能够处理的char* 类型
  	//拿到了转化成C的字符串
  	char* cstr = _JString2CStr(env,jstr);
  	//获取到长度
  	int length = strlen(cstr);
  	int i;
  	//遍历字符串
  	for(i = 0; i<length; i++){
  	//C的字符串就是字符数组，通过char类型的指针拿到了字符数组的首地址，通过指针的位移运算，遍历到字符数组的每一个字节
  	//遍历的时候cstr已经修改好了
  		*(cstr+i) += 2;
  	}
  	//之后在把str转化成jstring
  	return (*env)->NewStringUTF(env,cstr);
  }
/*这里是解密的处理，这里是减回去就可以了
 * Class:     com_xu_jniworddemo_MainActivity
 * Method:    decodeInC
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_xu_jniworddemo_MainActivity_decodeInC (JNIEnv * env, jobject obj, jstring jstr){
  	char* cstr = _JString2CStr(env,jstr);
  		int length = strlen(cstr);
  		int i;
  		for(i = 0; i<length; i++){
  			*(cstr+i) -= 2;
  		}
  		return (*env)->NewStringUTF(env,cstr);
  }