#!/bin/env python

import plottery_wrapper as p

p.dump_plot(
        fnames = [
            "background.root",
            ],
        sig_fnames=[
            "signal.root",
            ],
        dirname="plots1",

        legend_labels=[
            "Background",
            ],
        signal_labels=[
            "Signal",
            ],

        extraoptions={
            "nbins":180,
            "signal_scale": "auto",
            },
        )
