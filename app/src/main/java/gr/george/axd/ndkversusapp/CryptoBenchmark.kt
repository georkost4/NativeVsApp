package gr.george.axd.ndkversusapp

object CryptoBenchmark {
    fun sha256Kotlin(data: ByteArray): ByteArray {
        val digest = java.security.MessageDigest.getInstance("SHA-256")
        return digest.digest(data)
    }
}