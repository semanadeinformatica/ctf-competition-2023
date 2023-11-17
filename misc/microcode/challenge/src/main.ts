import { std, hono } from "./deps.ts";
import { compile } from "./compiler.ts";
import { thisDir } from "./dir.ts";

const { join } = std.path;
const { Hono, validator } = hono;
const { serveStatic, poweredBy, logger } = hono.middleware;

const app = new Hono();

app.use("*", logger());
app.use("*", poweredBy());

app.post(
  "/compile.php",
  validator("form", (data, ctx) => {
    const zip = data["zip"];
    if (!zip || typeof zip === "string") {
      return ctx.text("Invalid zip", 400);
    }

    return {
      zip,
    };
  }),
  async (ctx) => {
    const { zip } = await ctx.req.valid("form");

    const compilationResult = await compile(zip);
    
    if (!compilationResult.ok) {
        console.error(compilationResult.output);
        
        return ctx.text(`A compilation error occurred! Please correct your microcode and compile again.\n\n${compilationResult.output}`, 400);
    }

    const handle = await Deno.open(compilationResult.path);

    return ctx.body(handle.readable, {
      headers: {
        "Content-Type": "application/octet-stream",
        "Content-Disposition": "attachment; filename=microcode",
      },
    });
  }
);

app.use(
  "*",
  serveStatic({
    root: join(thisDir, "static"),
    rewriteRequestPath: (path) => path.replaceAll(".php", ".html"), // they won't know, how would they know?
  })
);

Deno.serve({'port': 8000, 'hostname': '0.0.0.0'}, app.fetch);
