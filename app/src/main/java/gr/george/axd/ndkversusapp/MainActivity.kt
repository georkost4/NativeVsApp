package gr.george.axd.ndkversusapp

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import gr.george.axd.ndkversusapp.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        val data = ByteArray(170 * 1024 * 1024) { it.toByte() } // 100MB

//        uncomment to test sha
//        val result = testSha(data)
        val result = testByteSum(data)
        binding.sampleText.text = result
    }

    private fun testByteSum(data: ByteArray): String {
        val kotlinTime = Computation.sumBytesExecutionTime(data)
        val nativeTime = nativeSimpleComputation(data)
        return """
                Kotlin :     $kotlinTime ms
                Native :    $nativeTime ms
            """.trimIndent()
    }

    private fun testSha(data: ByteArray): String {
        val kotlinStart = System.currentTimeMillis()
        CryptoBenchmark.sha256Kotlin(data)
        val kotlinTime = System.currentTimeMillis() - kotlinStart

        val nativeTime = nativeSha256(data)

        val opensslTime = nativeSha256OpenSSL(data)

        val result = """
                    Kotlin SHA-256:     $kotlinTime ms
                    Custom C SHA-256:   $nativeTime ms
                    OpenSSL SHA-256:    $opensslTime ms
                """.trimIndent()
        return result
    }

    /**
     * A native method that is implemented by the 'ndkversusapp' native library,
     * which is packaged with this application.
     */
    external fun nativeSha256(input: ByteArray): Long

    external fun nativeSha256OpenSSL(input: ByteArray): Long
    external fun nativeSimpleComputation(input: ByteArray): Long


    companion object {
        // Used to load the 'ndkversusapp' library on application startup.
        init {
            System.loadLibrary("ndkversusapp")
        }
    }
}