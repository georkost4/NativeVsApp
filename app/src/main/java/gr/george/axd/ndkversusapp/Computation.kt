package gr.george.axd.ndkversusapp

object Computation {
    fun sumBytesExecutionTime(data: ByteArray): Long {
        var sum: Long = 0
        val startTime = System.nanoTime()

        // Simple computation example: sum up byte values
        for (byte in data) {
            sum += byte.toLong() // Or byte.toLong() xor (data.indexOf(byte) % 256)
        }

        val endTime = System.nanoTime()
        return (endTime - startTime) / 1_000_000 // Convert nanoseconds to milliseconds
    }
}