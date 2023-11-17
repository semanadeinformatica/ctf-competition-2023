import { std } from "./deps.ts";

export const thisDir = std.path.relative(
    Deno.cwd(),
    std.path.dirname(
        std.path.fromFileUrl(import.meta.url)
    )
);