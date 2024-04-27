#!/bin/bash
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )

cd "$parent_path"

${VULKAN_SDK}/bin/glslangValidator -V shader.vert -o vert.spv -g
${VULKAN_SDK}/bin/glslangValidator -V shader.frag -o frag.spv -g
