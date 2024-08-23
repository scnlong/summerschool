---
title:  Introduction to supercomputing
event:  CSC Summer School in High-Performance Computing 2024
lang:   en
---

# This lecture

- What is High-performance computing?
- What kind of research can benefit from HPC?
- Anatomy of supercomputers
- Cloud computing
- Future of high-performance computing

# What is high-performance computing?

- Utilizing computing power that is much larger than available in a typical desktop computer
- Performance of HPC systems (i.e. supercomputers) is often measured in floating point operations per second (flop/s)
    - For software, other measures can be more meaningful
- Currently, the most powerful system reaches > $10^{18}$ flop/s (1 Eflop / s)

# What is high-performance computing?

<!-- Copyright CSC -->
 ![](img/cray.png){.center width=30%}

# What is high-performance computing?

<!-- Copyright CSC -->
 ![](img/LUMI_supercomputer.png){.center width=65%}

# Top 500 list

<!-- Source: top500.org, Copyright 1993-2023 TOP500.org (c) -->
 ![](img/top_500.png){.center width=48%}

# What are supercomputers used for? {.section}

# Application areas

- Fundamental sciences such as particle physics and cosmology
- Climate, weather and earth sciences
- Life sciences and medicine
- Chemistry and material science
- Energy, e.g renewable sources and fusion research
- Engineering, e.g. manufacturing and infrastructure
- etc.

# General use cases

- Problems that are hard to experiment on
    - Simulations with decade-long timescales
- Simulations of very different scales
    - From subatomic particles to cosmic scales
- Problems with very large datasets
- Complex computational problems
- Many of these are very time consuming, or even<br>
  impossible to solve on a standard computer

# Climate and weather research

<div class=column>
- Simulating ice sheets, air pollutants, sea-level rise etc.
- Building short and long-term simulations
- Simulated areas can span over countries or continents
- Modeling space weather
</div>
<div class=column>
![](img/climate_greenland.png){.center width=90%}
</div>

# Covid-19 fast track with Puhti

<div class=column>
- Modeling particles in airflows
- A large part of the calculations used for solving turbulent flow
- A third of Puhti was reserved for running the simulations
- The results have had an impact on e.g. ventilation instructions and the use of masks
</div>
<div class=column>
![](img/covid.png){.center width=100%}
</div>

#  Topological superconductors

<div class=column>
- Topological superconductors are possible building blocks for qubits
- Based on an elusive quantum state of electrons in thin layers
- Electronic properties simulated with the density-functional theory
    - These confirm that experimentally measured signals are due to this special quantum state
</div>
<div class=column>
![](img/majorana.png){.center width=100%}
</div>

# Deep language model of Finnish

<div class=column>
- Web-scale Finnish language data together with very deep neural networks utilizing GPUs
- Open GPT-3 model ("Finnish ChatGPT")
- The large language model "Poro"
</div>
<div class=column>
<!-- Source: Adobe Stock, CC BY-SA 3.0 -->
 ![](img/DeepFin.jpg){.center width=100%}
</div>

# Utilizing HPC in scientific research

<!-- Copyright CSC -->
 ![](img/sci.png){.center width=40%}

- **Goal for this school: everyone is able to write and modify HPC applications!**

# What are supercomputers made of? {.section}

# CPU frequency development

- Power consumption of CPU: $~f^3$

 ![](img/moore.png){.center width=45%}

# Parallel processing

- Modern (super)computers rely on parallel processing
- **Multiple** CPU cores & accelerators (GPUs)
    - `#`1 system has `~`600 000 CPU cores and `~`40 000 GPUs
    - `#`5 system (CPU-only) has `~`8 000 000 cores
- Vectorization
    - A single instruction can process multiple data (SIMD)
- Instruction level parallelism and pipelining
    - Core executes multiple instructions in parallel (superscalar execution)
    - Core executes different parts of instructions in parallel


# Anatomy of a supercomputer

<!-- Copyright CSC -->
 ![](img/anatomy.svg){.center width=55%}

- Supercomputers consist of nodes connected by a high-speed network
    - Latency `~`1 µs, bandwidth `~`100 GB / s
- A node can contain several multicore CPUs and several GPUs
- Memory within the node is directly usable by all CPU cores

# Supercomputer autopsy – Lumi

 ![](img/lumi.png){.center width=50%}

# From laptop to Tier-0

<div class=column>

<!-- Copyright CSC -->
 ![](img/tier.png){.center width=80%}

</div>
<div class=column>
- The most fundamental difference between a small university cluster and Tier-0 supercomputer is the number of nodes
    - The interconnect in high end systems is often also more capable
</div>

# Cloud computing {.section}

# Cloud computing

- Cloud infrastructure is run on top of normal HPC system:
    - Shared memory nodes connected by network
- User obtains **virtual** machines
- Several providers also offer bare metal instances
- Infrastructure as a service (IaaS)
    - User has full freedom (and responsibility) of operating system and the whole software environment
- Platform as a service (PaaS)
    - User develops and runs software within the provided environment

# Cloud computing and HPC

- Suitability of cloud computing for HPC depends heavily on application
- Virtualization adds overhead especially for the networking
- Bare metal cloud resources with high-speed interconnects can provide similar performance as traditional cluster
- Moving data out from the cloud can be time-consuming (and have a monetary cost)
- Cost-effectiveness of cloud depends heavily on the use case

# Future of High-performance computing {.section}

# Quantum computing

<div class=column>
- Solving certain types of problems exponentially faster than classical computers
- General purpose quantum computer is still far away
- Use cases still largely experimental and hypothetical
- Hybrid approaches
</div>
<div class=column>
![](img/quantum.png){.center width=50%}
</div>


# Post-Exascale challenges

- Performance of supercomputers has increased exponentially for a long time
- However, there are still challenges in continuing onwards from exascale supercomputers ($> 1 \times 10^{18}$ flop/s)
    - Power consumption: current `#`1 energy efficient system requires `~`20 MW for exascale performances
    - Manufacturing: Transistor sizes being extremely small 
    - Application scalability: how to program for 100 000 GPUs / 100 000 000 cores?

# Summary

- HPC reaches a lot of different fields of research
- Supercomputers base their performance on extreme parallelism
    - And GPUs nowadays
- Cloud computing as an option for accessing HPC resources
- The future of HPC looks bright but presents unique challenges