import { std, dax } from "./deps.ts";

const { join } = std.path;
const { $ } = dax;

type CompilationResult = 
    | { ok: true; output: string; path: string }
    | { ok: false; output: string };

export async function compile(zip: File): Promise<CompilationResult>  {
    // Create a temporary directory to compile the rust code
    const baseDir = await Deno.makeTempDir({ prefix: "sinf-microcode-" });

    // Write the provided zip file to the temporary directory
    const zipLocation = join(baseDir, "project.zip");
    await Deno.writeFile(zipLocation, zip.stream());

    // Unzip the provided zip file
    const projectDir = join(baseDir, "project");
    await $`unzip -q ${zipLocation} -d ${projectDir}`.printCommand();

    // Remove cache files, if present
    const targetDir = join(projectDir, "target");
    await Deno.remove(targetDir, { recursive: true }).catch(() => {});

    // Remove the instalation directory, if present
    const outDirPath = join(projectDir, "out");
    await Deno.remove(outDirPath, { recursive: true }).catch(() => {});
    
    // Compile the rust project
    const buildResult = await $`cargo install -q --path ${projectDir} --root ${outDirPath} --target-dir ${targetDir} --offline`
        .printCommand()
        .noThrow()
        .stderr("piped");

    if (buildResult.code !== 0) {
        return {
            ok: false,
            output: buildResult.stderr,
        };
    }

    // Read the compiled binary
    const compiledBinaryDir = join(outDirPath, "bin");
    const compiledBinaries = Deno.readDir(compiledBinaryDir);
    for await (const compiledBinary of compiledBinaries) {
        if (compiledBinary.isFile) {
            const compiledBinaryPath = join(compiledBinaryDir, compiledBinary.name);
            return {
                ok: true,
                output: buildResult.stderr,
                path: compiledBinaryPath,
            };
        }
    }

    return {
        ok: false,
        output: "No compiled binary found!",
    };
}