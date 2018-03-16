# CSE 274 Final Report: Fourier Depth of Field

## Group Members

* Ziyang Li, A92070182
* Ziqi Gan, A91047610

## Paper Specification

#### Fourier Depth Of Field, TOG 2009

* Cyril Soler, INRIA, Grenoble University, CNRS
* Kartic Subr, UC Irvine
* Frédo Durand, MIT CSAIL
* Nicolas Holzschuch & François Sillion, INRIA, Grenoble University, CNRS

## Abstract

In this quarter we implemented the Fourier Depth of Field paper by prof. Cyril
Soler from INRIA. In this implementation we are mainly focusing on ideas of
how to use Fourier spectrum to analyze the aperture effect and do prediction
on sample amount to adaptive sample the scene to improve efficiency. By the end
we are able to generate some very interesting results, and the adaptive sampling
method does work pretty well.

> Notice that in the milestone specification we also mentioned the Layered Light
Field Reconstruction paper. But unfortunately we did only figure out how to do
the Fourier Depth of Field one. So we abandoned the idea of also implementing
that paper.

## Algorithms

The algorithm is an A-Priori adaptive sampling algorithm that splat the samples
based on two observations:

1. The out-of-focus area doesn't require profuse sampling on image space.
2. The in-focus regions doesn't require profuse sampling on the aperture.

Based on these two observations, we want to analyze the image plane frequency
distribution as well as lens (aperture) frequency. And by using 

### Stage 1: Light Field Propagation and Scene Analysis

### Stage 2: Path Tracing

### Stage 3: Reconstruction

## Result

### Cube Scene

### Dragon Scene

## Benchmark

### Cube Scene

### Dragon Scene

## Comparison to Original Work

## Limitations

## Future Work

## Conclusion

It is also noticeable that when we got stucked I sent out an email to prof.
Soler and got replied from him. Saying that this is one of the earliest work
so there are a lot of assumptions that are very conservative. From there on they
have developed more precise algorithms to do better prediction on sample amount.
But this is
