# Optimal Page Replacement Algorithm

## Project Overview

This module implements the Optimal Page Replacement algorithm as part of Week 4 of the Process Management and Operating Systems PBL project.

The objective is to simulate page replacement in memory, record the state of frames after each page reference, identify page hits and page faults, and calculate the corresponding ratios.

## My Role

**Team Member:** Shashwath  
**Module:** Optimal Page Replacement Algorithm

My responsibilities include:

- Implementing the Optimal Page Replacement algorithm in C.
- Tracking page references and memory frame states.
- Identifying page hits and page faults.
- Selecting the appropriate page for replacement based on future references.
- Calculating total hits, total faults, hit ratio, and fault ratio.
- Developing a test program to validate the implementation.
- Recording and documenting test results.
- Updating the module to use the shared `common.h` header maintained by the team.

## Files and Structure

```text
shashwath/
├── optimal.c
├── optimal.h
├── README.md
├── report.md
└── tests/
    ├── test_optimal.c
    └── test_results.md
```

The module uses the team's shared header located at `week4/src/Sameeha/common.h`.

## Algorithm Description

The Optimal Page Replacement algorithm replaces the page whose next use is farthest in the future.

When a page reference occurs:

1. Check whether the page is already present in a frame.
2. If present, record a page hit.
3. If absent, record a page fault.
4. If an empty frame is available, load the page into it.
5. Otherwise, examine future references and replace the page that will be needed farthest in the future, or will not be needed again.
6. Record the resulting frame states for the current reference.

This approach minimizes page faults for a given reference string when future references are known.

## Implementation Details

The implementation:

- Accepts a page-reference array, reference count, and frame count.
- Validates input parameters and rejects negative page numbers.
- Tracks frame contents for every reference.
- Records whether each reference produces a hit or fault.
- Records replacement information when an existing page is replaced.
- Calculates hit and fault ratios as percentages.
- Stores simulation results using the shared project data structures.

## Testing

The implementation was tested using the following reference string:

`7 0 1 2 0 3 0 4 2 3`

**Number of frames:** 3

### Test Results

| Metric | Result |
|---|---:|
| Total page references | 10 |
| Page hits | 4 |
| Page faults | 6 |
| Hit ratio | 40.00% |
| Fault ratio | 60.00% |

The observed results match the expected results for this test case.

### Test Procedure

The module was compiled using GCC with warning flags enabled:

```bash
gcc -Wall -Wextra -std=c11 shashwath/optimal.c shashwath/tests/test_optimal.c -o test_optimal
```

The test executable was run using:

```bash
./test_optimal
```

The test program verifies the resulting hit and fault counts and displays the frame state after every page reference.

## Integration

The module is designed to work with the shared data structures defined in the team's `common.h` header.

The implementation uses the shared `SimulationResult` and `SimulationStep` structures to store simulation statistics and frame states.

Integration with the other team members' FIFO and LRU implementations is required for the complete comparative analysis and GUI workflow.

## Limitations

- The Optimal algorithm requires knowledge of future page references.
- It is primarily useful as a benchmark for comparing practical page replacement algorithms.
- The current test program validates a specific reference string; additional test cases are recommended.

## Conclusion

The Optimal Page Replacement module has been implemented and tested using a reference string with three memory frames. The test produced four page hits and six page faults, resulting in a 40% hit ratio and a 60% fault ratio.

This module provides the Optimal algorithm component for the team's broader page replacement simulation and comparative analysis project.