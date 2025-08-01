My intention was to develop an application which uses ndk and draw a comparison between some procedure done in app code (java/kotlin) versus in c/c++ (native code).

Initially I thought of running the sha256 hashing algorithm. 

As you can see from the screenshots this was a failure. 

My implementation of sha256 which was taken from some blogspot was failing behind the kotlin variation. Then I used some well tested and well known implementation (open ssl)  of sha256. This made things better but it still was falling behind the kotlin implementation.
Finally I read that the kotlin implementation was it self optimized from android sdk and was it self native so this made the whole example fall short.

<img width="243" height="216" alt="image" src="https://github.com/user-attachments/assets/ccfab93f-79c4-423d-815b-cabab7c9afd5" />



Next idea was to do some simple byte addition - this time the native implementation won even by a small margin

A 50ms difference for a large 100MB input (e.g., 200ms vs 250ms) where NDK is faster by 50ms is a typical and expected result when comparing simple, CPU-bound array operations between optimized C/C++ via JNI and Kotlin on Android.

You can see that on older device the margin is bigger and actually slower. This is due to the Android run time implementation of that android version - for reference it was taken on android 8 and android 15 respectively

<img width="455" height="212" alt="image" src="https://github.com/user-attachments/assets/c3cd2a6a-faab-49db-818f-1dd48aceab48" />


## Conclusions
JNI Overhead's Variable Impact: Explain how JNI overhead isn't constant; it can be much more significant on older devices.
The "Tipping Point": For simple operations, JNI overhead can negate or even reverse the expected NDK performance lead, especially on older hardware.
Context Matters: Performance isn't just about "native is always faster." It depends heavily on the specific task, the device's hardware, the Android version, and how efficiently JNI is used.



