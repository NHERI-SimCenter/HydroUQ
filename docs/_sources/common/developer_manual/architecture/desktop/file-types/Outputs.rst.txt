.. _lblOutputs:

Outputs
===================

After DL assessment is complete, the workflow collects the EDP.csv, DM.csv, and DV.csv file produced for each building asset and aggregates the results into single output files. When run locally, the workflow returns the output in a CSV format which are located in the *results* folder. When run remotely, the workflow returns the output in a HDF format which are located in the job archive. The HDF files may be converted into CSV format as a post-processing step.


.. jsonschema:: File_Schema.json#/properties/Outputs/outputEDP

The header schema, followed by an example output, are provided:

.. csv-table:: OutputEDPSchema.csv
   :file: files/OutputEDPSchema.csv
   :header-rows: 4
   :align: center

.. jsonschema:: File_Schema.json#/properties/Outputs/outputDM

The header schema, followed by an example output, are provided:

.. csv-table:: OutputDMSchema.csv
   :file: files/OutputDMSchema.csv
   :header-rows: 3
   :align: center

.. jsonschema:: File_Schema.json#/properties/Outputs/outputDV

The header schema, followed by an example output, are provided:

.. csv-table:: OutputDVSchema.csv
   :file: files/OutputDVSchema.csv
   :header-rows: 4
   :align: center
