#pragma once

#include "constants.hpp"
#include "types.hpp"

void replicate_s_scanned_entries_every_cell(
    // in
    int query_num, 
    int nprobe,
    hls::stream<int> &s_scanned_entries_every_cell,
    // out
    hls::stream<int> (&s_scanned_entries_every_cell_ADC)[ADC_PE_NUM],
    hls::stream<int> &s_scanned_entries_every_cell_load_PQ_codes);



void replicate_s_scanned_entries_every_cell(
    // in
    int query_num, 
    int nprobe,
    hls::stream<int> &s_scanned_entries_every_cell,
    // out
    hls::stream<int> (&s_scanned_entries_every_cell_ADC)[ADC_PE_NUM],
    hls::stream<int> &s_scanned_entries_every_cell_load_PQ_codes) {

    for (int query_id = 0; query_id < query_num; query_id++) {

        for (int nprobe_id = 0; nprobe_id < nprobe; nprobe_id++) {

            int scanned_entries_every_cell = s_scanned_entries_every_cell.read();
            for (int s = 0; s < ADC_PE_NUM; s++) {
#pragma HLS UNROLL
                s_scanned_entries_every_cell_ADC[s].write(scanned_entries_every_cell);
            }
            s_scanned_entries_every_cell_load_PQ_codes.write(scanned_entries_every_cell);
        }
    }
}
