## API Description

### Engine

The engine class stands for a kind of "shader" in opengl - the engines will
have a functionality taking in a scene and render it to a image. A sample engine
could be, ray tracer, path tracer, depth map generator, sampling rate generator
and so on.

#### DepthTracer.cpp

The depth tracer will render pictures with depth map that maps a the objects
within the finite near plane and far plane to the color. Actually the depth
does not need to be strictly within the color space, since the image class and
color class does not restrict the size and use a floating point number directly.

### Image

Image is a kind of buffer which has an array of pixels for us to set the colors
on. It also has properties of width and height. The subclasses of image such
as Bitmap will provide some functionality of reading and writing files.

### Light

The lights are, lexically the lights in the scene. While they provide
functionality lighting up the scene, some area lights will also have some
physical properties to let rays intersect them. It is a general interface
for the actual lights to base on.

### Object

The objects are essentially what constructs the scene. Obviously they will
all have a functionality to check if a ray intersects the object. In the mean
time, they all have material and transform.

### Scene

The scene folder consists of almost fixed camera and scene file, both are core
features that the engines based on.

#### Scene.cpp

The scene consists of three things: camera, objects and lights. And it also
provides basic functionality that, given a ray, check if any object or any
light has intersected it.

Possible subclass of scene could be a scene which has a spatial bounding box
for each objects.

#### Camera.cpp

The camera is a object represents a pinhole camera with aperture and focal
distance. While it doesn't provide the functionality to generate an image on
its own, it has apis for the engines to generate base rays by giving a screen
sample and aperture sample. Since this project is mainly for depth of field,
we don't provide functionality for shutter speed and so on. But one can still
easily extend this class to a camera with shutter speed and take times into
account.
