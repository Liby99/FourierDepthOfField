# CSE 274 Project Milestone: Fourier Depth of Field

## Group Members

* Ziyang Li, A92070182
* Ziqi Gan, A91047610

## Paper Specification

#### Fourier Depth Of Field, TOG 2009

* Cyril Soler, INRIA, Grenoble University, CNRS
* Kartic Subr, UC Irvine
* Frédo Durand, MIT CSAIL
* Nicolas Holzschuch & François Sillion, INRIA, Grenoble University, CNRS

#### Layered Light Field Reconstruction for Defocus Blur, TOG 2015

* Karthik Vaidyanathan, Intel Corporation
* Jacob Munkberg, Intel Corporation
* Petrik Clarberg, Intel Corporation
* Marco Salvi, Intel Corporation

## Milestone Description

### Paper Decision

At the start of the quarter we proposed that we want to write project composited
by this paper, *Fourier Depth of Field* (2009, Soler et al), and another paper
also on defocus blur, *Layered Light Field Reconstruction for Defocus Blur*
(2015, Vaidyanathan et al). We also thought about implementing the motion blur
effect in our renderer. But now because of the paper difficulty we found it
very hard to add new motion blur features into our project. After careful
decision we still want to implement the effect for two depth of field papers.
We will discuss why we are kind of confident in implementing them all in the
later descriptions. But we still want to have the chance to not implement the
second one (Layered Light Field Reconstruction) if we are stuck on the first
one (Fourier Depth of Field).

### Knowledge Preparation

The Light Field Transportation concept is really new to both of us, and we
really need time to digest these concepts. Luckily we have both done the class
presentation on the papers. Ziyang has presented the two papers that buildup
our project, and Ziqi has presented the *Frequency Analysis and Sheared
Reconstruction for Rendering Motion Blur* (K.Egan et al. 2009). All of these
papers are consists of ideas of Light Field Transport. And preparing for the
presentation is really pushing us to digest the concepts deeper. We held some
small meetings together and discuss the concepts, and we also went to the office
hour by Jiyang Yu to figure out the implementing problems. We also watched
Marc Levoy's Google Lectures on Digital Photography to get a better sense of
how apertures and cameras works. After all these preparations, we finally feel
like we can actually start building up the structures of our project and start
on implementing the details.

### Implementation-wise Setup

We both have basic Raytracer project done in CSE 167 Winter 2017. And in
Ziyang's case he has a more advanced version of the Raytracer he did in CSE 168.
And when we are designing the code structure of our new Raytracer and
Reconstructor, we really want to reuse the codes we already have.

In the sense of completely reusing the code, it is actually not possible because
for the final project in CSE 168, Ziyang implemented lots of effects and even
animation system where our reconstruction algorithms doesn't need (and even
cannot have). So it is a shame to not able to use the code already. But we found
it very interesting that we can still use most of it and add more detail and
more general interface design to do different features, which led us confident
on completing the two projects.

What we want to setup is actually an `Engine` class that can perform different
rendering methods to the same `Scene` structure. And we also have a
`LightFieldRay` class inherited from simple `Ray` class to compute light field
transport. The sample `Engine` class we have already resettled up is a
`PathTracer` engine that use the basic Monte Carlo Estimation over aperture
to render Depth of Field effects. The generated images are shown in the next
section.

The Raytracer we previously have is much different than what we are designing
right now, so it took us lots of time to setup.

### Current Naïve PathTracer Renderer Result

Four Stanford Dragons with different material are placed on a finite plane.

The picture below are two images with different focal distance and same aperture
size. The first picture has focal point on the dragons, and the second picture
has focal point behind them. This is done with very naïve path-tracer, with
bounce amount 5 and super-sampling per pixel 100.

![alt dragon_1][d1]

![alt dragon_2][d2]

### Future Steps

We are definitely going to work on Fourier Depth of Field first as the structure
of it is closer to our existing structure. And after doing that we will start
working on Layered Light Field Reconstruction.

It is also noticeable that for the both rendering methods we are going to highly
reuse the same set of code from `PathTracer`. This is not only enabling us to
write codes efficiently but also giving us a better chance to do benchmarks
using the same RayTracer on different reconstruction methods.

#### Fourier Depth of Field

For this, we are going to create a new engine `FDOFPathTracer`. Inside the
engine, we are going to separate the procedure into three stages. Note that the
`FDOFPathTracer` will be inheriting `PathTracer` because actually one stage of
it is just doing path tracing for the given samples

1. The first one is generating the samples by propagating the light fields. We
are going to create `LightFieldRay` class and do frequency domain sampling to
finally get the bandwidth of the pixel as well as aperture variance to generate
samples.

2. We are going to run `PathTracer::pathTrace(samples)` which is already done
for the given samples we had in stage 1.

3. We are going to create another class `FDOFReconstructor` which has a function
called `reconstruct(samples)`. This is just a post processing unit to
reconstruct the image.

#### Layered Light Field Reconstruction

For the Layered Light Field Reconstruction, we are going to create a new engine
`LLFRPathTracer` which is also inherited from `PathTracer`. We will render the
whole scene and let the renderer return extra information of the z-depth of
each sample. After that we will use the z-depths to divide the scene into
layers, generate filters for each layer and finally do reconstruct from all the
layers. We still have not detailedly design the structure of this part but it is
already making sense.

### Quarter Schedule

- Week 5 (Current Week): Completely Design the Structures of Project
- Week 6: Work on Fourier Depth of Field Path Tracer
- Week 7: Finalize Fourier Depth of Field Path Tracer
- Week 8: Work on Layered Light Field Reconstruction Path Tracer
- Week 9: Finalize Layered Light Field Reconstruction Path Tracer
- Week 10: Do benchmark and result demonstration, write project report and do
presentation.

[d1]: https://github.com/Liby99/FourierDepthOfField/raw/master/docs/res/milestone/dragon_1.bmp "Dragon 1"
[d2]: https://github.com/Liby99/FourierDepthOfField/raw/master/docs/res/milestone/dragon_2.bmp "Dragon 2"
