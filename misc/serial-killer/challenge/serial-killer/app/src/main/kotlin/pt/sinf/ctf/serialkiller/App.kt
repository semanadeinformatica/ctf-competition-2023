package pt.sinf.ctf.serialkiller

import java.nio.file.Path


fun main(args: Array<String>) {
    val serializationService = SerializationService()
    val encryptionServicePath = Path.of("encryption_service.dat")
    val flagPath = Path.of("flag.dat")

    val encryptionService = serializationService.restore(encryptionServicePath, EncryptionService::class) {
        EncryptionService()
    }

    val flag = serializationService.restore(flagPath, String::class) {
        encryptionService.encrypt(args[0])
    }

    Runtime.getRuntime().addShutdownHook(Thread {
        serializationService.save(encryptionServicePath, encryptionService)
        serializationService.save(flagPath, flag)
    })

    if (args.isNotEmpty()) {
        return
    }

    while (true) Thread.sleep(10000)
}
