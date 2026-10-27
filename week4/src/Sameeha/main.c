#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "common.h"
#include "../Joannes/fifo.h"
#include "../Riya/lru.h"
#include "../shashwath/optimal.h"

#define LRU_MAX_PAGES 100
#define LRU_FRAME_LIMIT 20

/* --------------------------------------------------
   Helper: append formatted text to an output buffer
   -------------------------------------------------- */

static int append_text(
    char *output,
    size_t output_size,
    size_t *used,
    const char *format,
    ...
)
{
    if (output == NULL || used == NULL || *used >= output_size)
        return -1;

    va_list args;
    va_start(args, format);

    int written = vsnprintf(
        output + *used,
        output_size - *used,
        format,
        args
    );

    va_end(args);

    if (written < 0 || (size_t)written >= output_size - *used)
        return -1;

    *used += (size_t)written;

    return 0;
}

/* --------------------------------------------------
   FIFO algorithm adapter
   -------------------------------------------------- */

static int run_fifo(
    const int pages[],
    int page_count,
    int frame_count,
    SimulationResult *result
)
{
    if (pages == NULL || result == NULL ||
        page_count <= 0 ||
        page_count > MAX_REFERENCES ||
        frame_count <= 0 ||
        frame_count > MAX_FRAMES)
    {
        return -1;
    }

    int hits = 0;
    int faults = 0;

    if (!fifo_page_replacement(
            pages,
            page_count,
            frame_count,
            &hits,
            &faults))
    {
        return -1;
    }

    memset(result, 0, sizeof(*result));

    result->algorithm = ALGORITHM_FIFO;
    result->frame_count = frame_count;
    result->total_references = page_count;
    result->total_hits = hits;
    result->total_faults = faults;

    result->hit_ratio = 100.0 * hits / page_count;
    result->fault_ratio = 100.0 * faults / page_count;

    int frames[MAX_FRAMES];
    int count = 0;
    int next = 0;

    for (int j = 0; j < frame_count; j++)
        frames[j] = -1;

    for (int i = 0; i < page_count; i++)
    {
        int found = 0;

        for (int j = 0; j < frame_count; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        SimulationStep *step = &result->steps[i];

        step->page = pages[i];
        step->status = found ? PAGE_HIT : PAGE_FAULT;
        step->replaced_page = -1;
        step->replaced_frame = -1;

        if (!found)
        {
            if (count < frame_count)
            {
                frames[count++] = pages[i];
            }
            else
            {
                step->replaced_page = frames[next];
                step->replaced_frame = next;

                frames[next] = pages[i];
                next = (next + 1) % frame_count;
            }
        }

        for (int j = 0; j < frame_count; j++)
            step->frames[j] = frames[j];
    }

    return 0;
}

/* --------------------------------------------------
   LRU algorithm adapter
   -------------------------------------------------- */

static int run_lru(
    const int pages[],
    int page_count,
    int frame_count,
    SimulationResult *result
)
{
    if (pages == NULL || result == NULL ||
        page_count <= 0 || page_count > MAX_REFERENCES ||
        frame_count <= 0 || frame_count > MAX_FRAMES)
    {
        return 0;
    }

    if (!lru_simulate(
            pages,
            page_count,
            frame_count,
            result))
    {
        return 0;
    }

    return 1;
}

/* --------------------------------------------------
   Optimal algorithm adapter
   -------------------------------------------------- */

static int run_optimal(
    const int pages[],
    int page_count,
    int frame_count,
    SimulationResult *result
)
{
    if (pages == NULL || result == NULL ||
        page_count <= 0 || page_count > MAX_REFERENCES ||
        frame_count <= 0 || frame_count > MAX_FRAMES)
    {
        return -1;
    }

    if (optimal_page_replacement(
            pages,
            page_count,
            frame_count,
            result) != 0)
    {
        return -1;
    }

    return 0;
}




/* --------------------------------------------------
   Format results for terminal or GUI output
   -------------------------------------------------- */

static int format_result(
    const SimulationResult *result,
    char *output,
    size_t output_size,
    size_t *used
)
{
    if (result == NULL || output == NULL || used == NULL)
        return -1;

    const char *name = "Unknown";

    switch (result->algorithm)
    {
        case ALGORITHM_FIFO:
            name = "FIFO";
            break;

        case ALGORITHM_LRU:
            name = "LRU";
            break;

        case ALGORITHM_OPTIMAL:
            name = "Optimal";
            break;

        default:
            break;
    }

    if (append_text(
            output, output_size, used,
            "\n========================================\n"
            "       %s PAGE REPLACEMENT\n"
            "========================================\n",
            name) != 0)
    {
        return -1;
    }

    if (append_text(
            output, output_size, used,
            "Page\tFrames\t\tStatus\n") != 0)
    {
        return -1;
    }

    for (int i = 0; i < result->total_references; i++)
    {
        const SimulationStep *step = &result->steps[i];

        if (append_text(
                output, output_size, used,
                "%d\t", step->page) != 0)
        {
            return -1;
        }

        for (int j = 0; j < result->frame_count; j++)
        {
            if (append_text(
                    output, output_size, used,
                    "%s",
                    step->frames[j] == -1
                        ? "- "
                        : "") != 0)
            {
                return -1;
            }

            if (step->frames[j] != -1)
            {
                if (append_text(
                        output, output_size, used,
                        "%d ", step->frames[j]) != 0)
                {
                    return -1;
                }
            }
        }

        if (append_text(
                output, output_size, used,
                "\t%s\n",
                step->status == PAGE_HIT ? "HIT" : "FAULT") != 0)
        {
            return -1;
        }
    }

    return append_text(
        output, output_size, used,
        "----------------------------------------\n"
        "Total references : %d\n"
        "Page hits        : %d\n"
        "Page faults      : %d\n"
        "Hit ratio        : %.2f%%\n"
        "Fault ratio      : %.2f%%\n",
        result->total_references,
        result->total_hits,
        result->total_faults,
        result->hit_ratio,
        result->fault_ratio
    );
}

/* --------------------------------------------------
   Run selected algorithms and return results as text.
   This function is intended for the GTK GUI.
   Returns 1 on success and 0 on failure.
   -------------------------------------------------- */

int run_simulation_to_text(
    const int pages[],
    int page_count,
    int frame_count,
    AlgorithmType selected_algorithm,
    char *output,
    size_t output_size
)
{
    if (pages == NULL || output == NULL ||
        output_size == 0 ||
        page_count <= 0 ||
        page_count > MAX_REFERENCES ||
        frame_count <= 0 ||
        frame_count > MAX_FRAMES ||
        selected_algorithm < ALGORITHM_FIFO ||
        selected_algorithm > ALGORITHM_ALL)
    {
        return 0;
    }

    if (selected_algorithm == ALGORITHM_LRU ||
        selected_algorithm == ALGORITHM_ALL)
    {
        if (page_count > LRU_MAX_PAGES ||
            frame_count > LRU_FRAME_LIMIT)
        {
            snprintf(
                output,
                output_size,
                "LRU supports at most %d references "
                "and %d frames with the current implementation.",
                LRU_MAX_PAGES,
                LRU_FRAME_LIMIT
            );

            return 0;
        }
    }

    output[0] = '\0';

    size_t used = 0;

    SimulationResult results[3];
    int result_count = 0;

    if (selected_algorithm == ALGORITHM_FIFO ||
        selected_algorithm == ALGORITHM_ALL)
    {
        if (run_fifo(
                pages, page_count, frame_count,
                &results[result_count]) != 0)
        {
            snprintf(output, output_size, "FIFO simulation failed.");
            return 0;
        }

        if (format_result(
                &results[result_count],
                output, output_size, &used) != 0)
        {
            snprintf(output, output_size, "Output buffer is too small.");
            return 0;
        }

        result_count++;
    }

    if (selected_algorithm == ALGORITHM_LRU ||
        selected_algorithm == ALGORITHM_ALL)
    {
        if (run_lru(
                pages, page_count, frame_count,
                &results[result_count]) == 0)
        {
            snprintf(output, output_size, "LRU simulation failed.");
            return 0;
        }

        if (format_result(
                &results[result_count],
                output, output_size, &used) != 0)
        {
            snprintf(output, output_size, "Output buffer is too small.");
            return 0;
        }

        result_count++;
    }

    if (selected_algorithm == ALGORITHM_OPTIMAL ||
        selected_algorithm == ALGORITHM_ALL)
    {
        if (run_optimal(
                pages, page_count, frame_count,
                &results[result_count]) != 0)
        {
            snprintf(output, output_size, "Optimal simulation failed.");
            return 0;
        }

        if (format_result(
                &results[result_count],
                output, output_size, &used) != 0)
        {
            snprintf(output, output_size, "Output buffer is too small.");
            return 0;
        }

        result_count++;
    }

    if (selected_algorithm == ALGORITHM_ALL)
    {
        if (append_text(
                output, output_size, &used,
                "\n========== ALGORITHM COMPARISON ==========\n"
                "%-12s %-12s %-12s\n",
                "Algorithm", "Hits", "Faults") != 0)
        {
            snprintf(output, output_size, "Output buffer is too small.");
            return 0;
        }

        for (int i = 0; i < result_count; i++)
        {
            const char *name =
                results[i].algorithm == ALGORITHM_FIFO ? "FIFO" :
                results[i].algorithm == ALGORITHM_LRU ? "LRU" :
                "Optimal";

            if (append_text(
                    output, output_size, &used,
                    "%-12s %-12d %-12d\n",
                    name,
                    results[i].total_hits,
                    results[i].total_faults) != 0)
            {
                snprintf(output, output_size, "Output buffer is too small.");
                return 0;
            }
        }
    }

    return 1;
}

/* --------------------------------------------------
   Original terminal simulation function
   -------------------------------------------------- */

int run_simulation(
    const int pages[],
    int page_count,
    int frame_count,
    AlgorithmType selected_algorithm
)
{
    char output[100000];

    if (!run_simulation_to_text(
            pages,
            page_count,
            frame_count,
            selected_algorithm,
            output,
            sizeof(output)))
    {
        printf("%s\n", output[0] ? output : "Simulation failed.");
        return 0;
    }

    printf("%s", output);
    return 1;
}

/* --------------------------------------------------
   Terminal main.
   Excluded when compiling the GTK application.
   -------------------------------------------------- */

#ifndef PAGE_REPLACEMENT_GUI

int main(void)
{
    int pages[MAX_REFERENCES];
    int page_count = 0;
    int frame_count;
    int choice;

    char input[4096];

    printf("========================================\n");
    printf("   PAGE REPLACEMENT SIMULATOR\n");
    printf("========================================\n");

    printf("Enter page references separated by spaces:\n");

    if (fgets(input, sizeof(input), stdin) == NULL)
        return 1;

    char *token = strtok(input, " ,\t\n");

    while (token != NULL)
    {
        char *end;
        long value = strtol(token, &end, 10);

        if (*end != '\0' || value < 0 ||
            value > 2147483647L ||
            page_count >= MAX_REFERENCES)
        {
            printf("Invalid page reference input.\n");
            return 1;
        }

        pages[page_count++] = (int)value;
        token = strtok(NULL, " ,\t\n");
    }

    if (page_count == 0)
    {
        printf("No page references entered.\n");
        return 1;
    }

    printf("Enter number of frames (1-%d): ", MAX_FRAMES);

    if (scanf("%d", &frame_count) != 1 ||
        frame_count < 1 || frame_count > MAX_FRAMES)
    {
        printf("Invalid frame count.\n");
        return 1;
    }

    printf("\nChoose algorithm:\n");
    printf("1. FIFO\n");
    printf("2. LRU\n");
    printf("3. Optimal\n");
    printf("4. Compare all\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1 ||
        choice < 1 || choice > 4)
    {
        printf("Invalid algorithm choice.\n");
        return 1;
    }

    return run_simulation(
        pages,
        page_count,
        frame_count,
        (AlgorithmType)choice
    ) ? 0 : 1;
}

#endif