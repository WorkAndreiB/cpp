# Base image
FROM ubuntu:24.04

# Set working directory
WORKDIR /ros2

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    make \
    cmake \
    perl \
    curl \
    python3-dev \
    python3-venv \
    python3-pip \
    git \ 
    terminator \
    && apt-get clean
    
# Create and activate virtual environment
RUN python3 -m venv /opt/venv

# Make sure the venv pip is up-to-date
RUN /opt/venv/bin/pip install --upgrade pip

# Add virtual environment to PATH
ENV PATH="/opt/venv/bin:$PATH"

# Environment settings
ENV PYTHONUNBUFFERED=1

# Default command
CMD ["bash"]

WORKDIR /workspace
