# Vec23

![Language](https://img.shields.io/badge/language-C%2B%2B20-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

**A lean library of vectors and quaternions written in modern C++.**

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

## Features
* **Modern:** Designed to be imported as a C++20 module.
* **Flexible:** Supports all floating point types.
* **Backward Compatible:** Can be included as headers in older C++ versions.

## Installation
Copy the `include/Vec23` folder into your project's include path.

## Usage
```cpp
import Vec23;

// Vector2
Vector2<float> a(1.0f, 0.0f);
Vector2<float> b(2.0f, 0.0f);
float dot = a.Dot(b);

// Vector3
Vector3<float> a(1.0f, 0.0f, 0.0f);
Vector3<float> b(0.0f, -1.0f, 0.0f);
float angle = Vector3<float>::Angle(a, b);

// Quaternion
auto q = Quaternion<float>::FromAxisAngle({ 0.0f, 1.0f, 0.0f }, 90.0f);
Vector3<float> v(1.0f, 0.0f, 0.0f);
Vector3<float r = q.RotateVector(v);
```

## License
Distributed under the MIT License. See LICENSE for more information.
