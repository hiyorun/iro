# iroha

A template based colour palette generator. Using Google's Material Colour Utilities under the hood.

## Todos
- Batch template processings
- Template bracket escaping
- Add debug flags
- Make logs more human readable

## How to build
1. Create a directory called `build`
2. Change to that directory, and then `cmake ../`
3. Then execute `make`
```
mkdir build
cd build
cmake ../ && make
```

This code depends on `absl` and `imagemagick`

## How to use
```
iroha [OPTIONS]
```

You can pass the key colour to be used via `-c value`/`--colour <value>` in ARGB format like `ff432277` (aarrggbb). Or you can pass an image via `-m /path/to/image` or `--image /path/to/image`.

After that, you can output the colour scheme by template:
```
-i, --inja <template-path>   # Path to Inja template for the palette. This will require -o
-o, --output <path>          # Output path
```
Or you can just output plain JSON `-j`/`--json`

You can toggle dark mode by passing `-d`/`--dark-mode`

## Examples
```
iroha -j --colour ff902922
iroha -d -j -c ff902922
iroha -i template.css -o output.css -c ff902922
iroha -m poisonous-red-fluff.png -i template.css -o output.css
```

## Contribute
I have no code of conduct obviously. And I'm expecting that this codebase will not be that big. But if you could prove me wrong, I'll definitely going to tidy this repo up.

You can open a new [Issue](https://github.com/hiyorun/iroha/issues/new). Or if you can code, feel free to fork this and create a pull requests.
