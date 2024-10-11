cmake_minimum_required(VERSION 3.29)
project(HPC C)

set(CMAKE_C_STANDARD 11)

add_executable(HPC
    First_examples/broadcast.c
    First_examples/mpi_hello_world.c
    First_examples/mpi_hello_world_v2.c
    First_examples/ring.c)
