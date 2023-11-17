package pt.sinf.ctf.serialkiller

import java.io.Serializable
import java.util.Base64
import javax.crypto.Cipher
import javax.crypto.KeyGenerator
import javax.crypto.SecretKey
import javax.crypto.spec.IvParameterSpec

val CHARSET = Charsets.UTF_8

class EncryptionService: Serializable {
    
    companion object {
        val serialVersionUID: Long = 1L
    }

    private val key: SecretKey
    private val algorithm = "AES_128/OFB/NoPadding"
    private val keySize = 128
    private val iv = ByteArray(keySize / 8) { 0 }

    init {
        val generator = KeyGenerator.getInstance("AES")
        generator.init(keySize)
        
        this.key = generator.generateKey()
    }
    
    fun encrypt(text: String): String {
        val cipher = Cipher.getInstance(algorithm)
        val ivSpec = IvParameterSpec(iv)
        cipher.init(Cipher.ENCRYPT_MODE, key, ivSpec)
        
        val cipherText = cipher.doFinal(text.toByteArray(CHARSET))
        return Base64.getEncoder()
            .encodeToString(cipherText)
    }
    
    fun decrypt(encodedCipherText: String): String {
        val cipher = Cipher.getInstance(algorithm)
        val gcmSpec = IvParameterSpec(iv)
        cipher.init(Cipher.DECRYPT_MODE, key, gcmSpec)

        val cipherText = Base64.getDecoder()
            .decode(encodedCipherText)
        
        val text = cipher.doFinal(cipherText)
        return String(text, CHARSET)
    }
}