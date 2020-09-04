# Engine

Engine is a WIP project following my foray into game engine development.

## Installation

Get a copy of the repository and build using CMake

```bash
git clone --recurse-submodules git://github.com/beeryt/engine.git
mkdir engine/build
cd engine/build
cmake ..
make -j8
```

## Usage

Binary executables are located in `engine/build`

## Documentation

Documentation is generated using Doxygen.
Enable building documentation with the following CMake option:
```bash
cmake .. -DBUILD_DOCS=ON
make -j8
```

Freshly generated documentation can be found in `docs/html`.

## License
[MIT](https://choosealicense.com/licenses/mit/)
