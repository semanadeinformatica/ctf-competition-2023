package pt.sinf.ctf.serialkiller

import java.io.IOException
import java.io.ObjectInputStream
import java.io.ObjectOutput
import java.io.ObjectOutputStream
import java.nio.file.Files
import java.nio.file.OpenOption
import java.nio.file.Path
import java.nio.file.StandardOpenOption
import kotlin.reflect.KClass
import kotlin.reflect.cast

class SerializationService {
    fun <T : Any>restore(path: Path, clazz: KClass<T>, defaultValue: () -> T): T {
        var returnValue: T
        
        try {
            val serializedValue = Files.newInputStream(path)
            serializedValue.use {
                val stream = ObjectInputStream(it)
                returnValue = clazz.cast(stream.readObject())
            }

            Files.deleteIfExists(path)
        } catch (ignored: IOException) {
            returnValue = defaultValue()
        }
        
        return returnValue
    }

    fun <T: Any>save(path: Path, value: T) {
        val serializedValue = Files.newOutputStream(path)
        serializedValue.use {
            val stream = ObjectOutputStream(it)
            stream.writeObject(value)
        }
    }
}