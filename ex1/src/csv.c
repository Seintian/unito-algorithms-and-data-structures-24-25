#include "csv.h"
#include <errno.h>


const char* recordReadFmt = "%d,%99[^,],%d,%lf\n";
const char* recordWriteFmt = "%d,%s,%d,%lf\n";

int compare_field1(const void* a, const void* b) {
    return strcmp(((RecordPtr) a) -> field1, ((RecordPtr) b) -> field1);
}

int compare_field2(const void* a, const void* b) {
    return ((RecordPtr) a) -> field2 - ((RecordPtr) b) -> field2;
}

int compare_field3(const void* a, const void* b) {
    double res = (((RecordPtr) a) -> field3 - ((RecordPtr) b) -> field3);

    if (res < 0)
        return -1;

    else if (res > 0)
        return 1;

    else
        return 0;
}

size_t count_lines(FILE* file) {
    size_t n_lines = 0;
    char buffer[MAX_LINE_SIZE];

    while (fgets(buffer, MAX_LINE_SIZE, file))
        n_lines++;

    rewind(file);

    return n_lines;
}

size_t read_records(FILE* infile, RecordPtr records, size_t n_records) {
    size_t read_count = 0;
    char buffer[READING_BUFFER_SIZE];
    char line[MAX_LINE_SIZE];
    size_t bytes_read;
    char *start, *end;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), infile)) > 0 && read_count < n_records) {
        start = buffer;
        end = buffer + bytes_read;

        while (start < end && read_count < n_records) {
            char *newline = memchr(start, '\n', end - start);

            if (newline != NULL) {
                size_t line_length = newline - start;
                if (line_length < MAX_LINE_SIZE) {
                    memcpy(line, start, line_length);
                    line[line_length] = '\0';
                    
                    // Manually parse instead of using sscanf -> faster
                    char *token = strtok(line, ",");
                    records[read_count].id = atoi(token);

                    token = strtok(NULL, ",");
                    strcpy(records[read_count].field1, token);

                    token = strtok(NULL, ",");
                    records[read_count].field2 = atoi(token);

                    token = strtok(NULL, ",");
                    records[read_count].field3 = atof(token);

                    read_count++;
                }
                start = newline + 1;
            } 
            else {
                // Handle the case where a line extends beyond the buffer size.
                // Shift unprocessed data to the beginning of the buffer and read more data.
                break;
            }
        }

        // Handle any leftover data if needed.
        if (start < end)
            fseek(infile, -(end - start), SEEK_CUR);
    }

    if (ferror(infile)) {
        perror("Error reading from CSV file");
        exit(EXIT_FAILURE);
    }

    return read_count;
}


size_t write_records(FILE* outfile, RecordPtr records, size_t n_records) {
    size_t n_wrote_records = 0;
    char buffer[WRITING_BUFFER_SIZE];
    char *ptr = buffer;
    size_t buffer_left = sizeof(buffer);

    for (size_t i = 0; i < n_records; i++) {
        int written = snprintf(ptr, buffer_left, recordWriteFmt,
                               records[i].id,
                               records[i].field1,
                               records[i].field2,
                               records[i].field3);

        // If the current record doesn't fit, flush the buffer
        if (written >= buffer_left) {
            if (fwrite(buffer, 1, ptr - buffer, outfile) < ptr - buffer) {
                perror("Error writing to CSV file");
                exit(EXIT_FAILURE);
            }

            ptr = buffer;
            buffer_left = sizeof(buffer);

            // Write the current record directly if it's still too big for the buffer
            if (written >= sizeof(buffer)) {
                fprintf(outfile, recordWriteFmt,
                        records[i].id,
                        records[i].field1,
                        records[i].field2,
                        records[i].field3);
            } else {
                snprintf(ptr, buffer_left, recordWriteFmt,
                         records[i].id,
                         records[i].field1,
                         records[i].field2,
                         records[i].field3);
            }
        }

        // Move the pointer forward and adjust buffer_left
        ptr += written;
        buffer_left -= written;
        n_wrote_records++;
    }

    // Flush any remaining data in the buffer
    if (ptr != buffer)
        fwrite(buffer, 1, ptr - buffer, outfile);

    return n_wrote_records;
}

