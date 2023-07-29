
# Grapher: A Data Visualization Tool

Welcome to the Grapher project! This repository contains a robust and versatile C++ program that generates insightful graphs based on input data. It's a powerful tool designed for data analysts, researchers, and anyone interested in visualizing complex data sets.

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Getting Started](#getting-started)
4. [Usage](#usage)
5. [Contributing](#contributing)
6. [Example of an output](#Example of an output)


## Overview

The heart of this project is `grapher.C`, a C++ program that takes in data and generates a corresponding graph. The program leverages the power of the ROOT library, a modular scientific software framework that provides all the functionalities needed to deal with big data processing, statistical analysis, visualization, and storage. 

Whether you're dealing with large-scale data from a research project or smaller datasets for personal projects, Grapher can help you visualize your data in a meaningful way.

## Features

- **Versatile Data Input**: Grapher can handle a wide range of data inputs, making it a flexible tool for various data analysis scenarios.
- **Integration with ROOT**: Grapher is built on the ROOT library, allowing it to handle complex data analysis tasks with ease.

## Getting Started

To get started with Grapher, you'll need to have the ROOT library installed on your system. You can find instructions for installing ROOT [here](https://root.cern/install/).

Once you have ROOT installed, you can compile the `grapher.C` program using the following command:

```bash
g++ grapher.C -c -o program.o $(root-config --cflags --libs)  

g++ program.o -o myProgram $(root-config --ldflags --libs) -lGenVector  
# an example of running over a root file called signal.root
./myProgram /home/users/eslam.zenhom/public_html/uf_work/vbs/analysis/output output.root signal.root 

```
git clone --branch rooutil++ git@github.com:sgnoohc/rooutil.git
source rooutil/bin/thisrooutil.sh 

source rooutil/bin/setuproot.sh 

python3 plot.py 

## Usage

To use the `grapher.C` program, you'll need to provide it with data. The program expects data in a specific format, so be sure to format your data correctly. More detailed instructions on how to format your data and use the program will be provided in the `USAGE.md` file.

## Contributing

Contributions to Grapher are always welcome! If you have a feature request, bug report, or proposal, please open an issue on this repository. We value your feedback and contributions to improve this tool.

## Example of an output



