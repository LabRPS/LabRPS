==========================
LabRPS build dependencies
==========================

Distributions
=============

The following commands are used to install the packages needed to build LabRPS from source on the following distributions.


Arch Linux
----------

The following command is used to install the required packages used to compile LabRPS on Arch Linux.

.. code-block:: console

    sudo sh tools/build/arch.sh


Debian
------

The following command is used to install the required packages used to compile LabRPS on Debian.

.. code-block:: console

    sudo sh tools/build/debian.sh


Fedora
------

The following command is used to install the required packages used to compile LabRPS on Fedora.

.. code-block:: console

    sudo sh tools/build/fedora.sh


Manjaro
-------

The following command is used to install the required packages used to compile LabRPS on Manjaro Linux.

.. code-block:: console

    sudo sh tools/build/manjaro.sh


Ubuntu
------


The following command is used to install the required packages used to compile LabRPS on Ubuntu Linux.

.. code-block:: console

    sudo sh tools/build/ubuntu.sh


Containers
==========

The following will create containers that have all the required dependencies
pre-installed that are needed to build LabRPS from source.


Arch Linux
-----------

The following commands are used to create and run a Arch Linux build environment.

.. code-block:: console

    docker build --file tools/build/Dockerfile.Arch --tag labrps-arch
    docker run --rm --interactive --tty --volume $(pwd):/builds:z labrps-arch


Debian
------

The following commands are used to create and run a Debian build environment.

.. code-block:: console

    docker build --file tools/build/Dockerfile.Debian --tag labrps-debian
    docker run --rm --interactive --tty --volume $(pwd):/builds:z labrps-debian


Fedora
------

The following commands are used to create and run a Fedora build environment.

.. code-block:: console

    docker build --file tools/build/Dockerfile.Fedora --tag labrps-fedora
    docker run --rm --interactive --tty --volume $(pwd):/builds:z labrps-fedora


Manjaro
-------

The following commands are used to create and run a Manjaro build environment.

.. code-block:: console

    docker build --file tools/build/Dockerfile.Manjaro --tag labrps-manjaro
    docker run --rm --interactive --tty --volume $(pwd):/builds:z labrps-manjaro


Ubuntu
------

The following commands are used to create and run a Ubuntu build environment.


.. code-block:: console

    docker build --file tools/build/Dockerfile.Ubuntu --tag labrps-ubuntu
    docker run --rm --interactive --tty --volume $(pwd):/builds:z labrps-ubuntu


Build Code
==========

To build the LabRPS code inside one of the running containers the following
commands should be used

.. code-block:: console

    mkdir labrps-build
    cd labrps-build
    cmake ../labrps-source
    make -j$(nproc --ignore=2)
