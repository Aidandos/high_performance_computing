#ifndef CONSTS_H_
#define CONSTS_H_

// maximum number of iterations
#define MAX_ITERS     35207

// image size
#define IMAGE_WIDTH   4096
#define IMAGE_HEIGHT  4096

// the extent of the parameter plane ( MIN_X + iMIN_Y <= c < MAX_X + iMAX_Y )
#define MIN_X   -2.1
#define MAX_X    0.7
#define MIN_Y   -1.4
#define MAX_Y    1.4

typedef struct
{
    long nx;
    long ny;
    long startx;
    long starty;
    long endx;
    long endy;
} Domain;

typedef struct
{
    int y;
    int x;
    int nx;
    int ny;
    MPI_Comm comm;
} Partition;

/**
Structure Partition represents the layout of the grid of processes
organized in the Cartesian communicator (p.comm) that needs to be created (MPI_Cart_create)
and contains information such as number of processes in x and y direction (p.nx, p.ny)
and the coordinates of the current MPI process (p.x, p.y).
*/

Partition createPartition(int mpi_rank, int mpi_size)
{
    Partition p;

    p.nx = 1;
    p.ny = 1;

    // divides it into p.nx by p.ny processes
    int dims[2];
    MPI_Dims_create(mpi_size, 2, dims);

    p.nx = dims[1];
    p.ny = dims[0];

    MPI_Comm comm_cart = MPI_COMM_WORLD;
    p.comm = comm_cart;

    int periods[2];
    periods[0]= 0;
    periods[1]= 0;

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &p.comm);

    p.x = 0;
    p.y = 0;

    int coords[2];
    MPI_Cart_coords(p.comm, mpi_rank, 2, coords);

    p.x = coords[1];
    p.y = coords[0];

    return p;
}

/**
Updates Partition structure to represent the process mpi_rank.
Copy the grid information (p.nx, p.ny and p.comm) and update
the coordinates to represent position in the grid of the given
process (mpi_rank)
*/
Partition updatePartition(Partition p_old, int mpi_rank)
{
    Partition p;

    p.ny = p_old.ny;
    p.nx = p_old.nx;
    p.comm = p_old.comm;

    int coords[2];
    MPI_Cart_coords(p.comm, mpi_rank, 2, coords);

    p.x = coords[1];
    p.y = coords[0];


    return p;
}

/**
Structure Domain represents the information about the local domain of the current MPI process.
It holds information such as the size of the local domain (number of pixels in each dimension - d.nx, d.ny)
and its global indices (index of the first and the last pixel in the full image of the Mandelbrot set
that will be computed by the current process d.startx, d.endx and d.starty, d.endy).
*/
Domain createDomain(Partition p)
{
    Domain d;

    d.nx = IMAGE_WIDTH / p.nx;
    d.ny = IMAGE_HEIGHT / p.ny;

    d.startx = p.x*d.nx;
    d.starty = p.y*d.ny;

    d.endx = d.startx + d.nx - 1;
    d.endy = d.starty + d.ny -1;

    return d;
}


#endif /*CONSTS_H_*/
