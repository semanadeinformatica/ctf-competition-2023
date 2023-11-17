export * as dax from "https://deno.land/x/dax@0.35.0/mod.ts";

// Standard library
import * as path from "https://deno.land/std@0.201.0/path/mod.ts";

export const std = {
    path,
};

// Hono
export const hono = Object.assign(
    {},
    await import("https://deno.land/x/hono@v3.7.6/mod.ts"),
    {
        middleware: await import("https://deno.land/x/hono@v3.7.6/middleware.ts"),
    }
);