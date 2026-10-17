"""
Make the README gallery from tools/gallery.txt.

For every function it runs ./MathPloText, turns the frames of the
animation into sample/functions/<name>.gif, and writes the gallery
between <!-- gallery --> and <!-- /gallery --> in README.md.

    make gallery                           # every function
    python3 tools/gallery.py              # the same, after make
    python3 tools/gallery.py heart soliton # only these gifs

Needs Pillow (pip install pillow) and the DejaVu Sans Mono font.
"""

import os
import re
import shlex
import subprocess
import sys
from multiprocessing import Pool

from PIL import Image, ImageDraw, ImageFont

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FONT = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 12)
CELL = FONT.getbbox("M")[2]
LINE = 15
COLOR = (139, 233, 253)


def read_gallery():
    """Categories, each with its functions."""
    categories = []
    for line in open(ROOT + "/tools/gallery.txt"):
        line = line.rstrip("\n")
        if not line:
            continue
        if line.startswith("# "):
            title, note = line[2:].split("|")
            categories.append({"title": title, "note": note, "items": []})
            continue
        name, title, desc, opts, exprs = line.split("|")
        categories[-1]["items"].append({
            "name": name, "title": title, "desc": desc,
            "opts": opts, "exprs": exprs.split(";;"),
        })
    return categories


def command(item):
    return "./MathPloText " + item["opts"] + " " + " ".join('"%s"' % e for e in item["exprs"])


def make_gif(item):
    args = ["./MathPloText"] + shlex.split(item["opts"]) + ["-d", "0"] + item["exprs"]
    out = subprocess.run(args, capture_output=True, text=True, cwd=ROOT).stdout

    lines = out.split("\n")
    legend = lines[:len(item["exprs"])]
    body = "\n".join(lines[len(item["exprs"]):])
    frames = [f.strip("\n") for f in re.split(r"\x1b\[\d+A", body) if f.strip()]

    #every other frame keeps the gif small; the last one stays on screen
    frames = frames[::2] + ([frames[-1]] if len(frames) % 2 == 0 else [])

    head = ["$ " + command(item)] + legend
    width = max(len(l) for l in head + frames[-1].split("\n")) * CELL + 24
    height = (len(head) + len(frames[-1].split("\n"))) * LINE + 16

    images = []
    for frame in frames:
        image = Image.new("RGB", (width, height), "black")
        draw = ImageDraw.Draw(image)
        for i, text in enumerate(head + frame.split("\n")):
            draw.text((12, 8 + i * LINE), text, font=FONT, fill=COLOR)
        images.append(image.quantize(colors=8))

    step = 120 if "-t" in item["opts"] else 70
    durations = [step] * (len(images) - 1) + [2500]
    images[0].save(ROOT + "/sample/functions/%s.gif" % item["name"], save_all=True,
                   append_images=images[1:], duration=durations, loop=0, optimize=True)
    return item["name"]


def html(text):
    text = text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
    return re.sub(r"`([^`]*)`", r"<code>\1</code>", text)


def write_readme(categories):
    out = ["<!-- gallery -->", ""]
    for category in categories:
        out += ["### " + category["title"], ""]
        if category["note"]:
            out += [category["note"], ""]
        out.append("<table>")
        items = category["items"]
        for i in range(0, len(items), 2):
            out.append("<tr>")
            for item in items[i:i + 2]:
                out += [
                    '<td width="50%" valign="top">',
                    '<img src="sample/functions/%s.gif" width="100%%"><br>' % item["name"],
                    "<b>%s</b>: %s<br>" % (html(item["title"]), html(item["desc"])),
                    "<sub><code>%s</code></sub>" % html(command(item)),
                    "</td>",
                ]
            out.append("</tr>")
        out += ["</table>", ""]
    out.append("<!-- /gallery -->")

    readme = open(ROOT + "/README.md").read()
    readme = re.sub(r"<!-- gallery -->.*<!-- /gallery -->", "\n".join(out), readme, flags=re.S)
    open(ROOT + "/README.md", "w").write(readme)


if __name__ == "__main__":
    categories = read_gallery()
    items = [item for c in categories for item in c["items"]]
    only = sys.argv[1:]
    if only:
        items = [item for item in items if item["name"] in only]

    with Pool() as pool:
        for name in pool.imap_unordered(make_gif, items):
            print(name)

    write_readme(categories)
