# Getting started
## Building the assignment
```bash
git clone https://gitlab.chpc.utah.edu/01404975/assignment1.git Prog-assignment1
cd Prog-assignment1
# chpc has default read permissions for everyone, we set correct permission
bash init.sh
source env.sh
make
```
## Setting up environment
   On CHPC machines, use command `source env.sh` every time you log in
   to any machine (when you login to chpc and any time you run `srun` or
   `salloc`. For now `env.sh` sets gcc version and creates `env.log` file which
   you can share if you face problems.<br/>
   Include output of `summary.sh` (`summary.log`) in your report. You can use
   `summary.sh` with `sbatch` command if you want.
   
## Correctness tests
   Running the Makefile should create three executables for the three problems and print 
   output reporting achieved performance of the code and status of correctness checks.
   Only make changes in files which end in -sol.c. You should not make any changes to
   any other files. The test harness for grading will use the given files, with the
   only substitution being your submitted files ending in -sol.c
   
## Performance tests
   We will use specific machines to measure the performance. Once your code is
   correct, get a notchpeak CHPC node using the command:
   ```bash
   srun -M notchpeak --account=owner-guest --partition=notchpeak-guest --nodes=1 --ntasks=1 -C c32 -t 0:05:00  --pty /bin/bash -l
   ```
   > Do not change `-C c32` and `--nodes=1 --ntasks=1` in above command! It makes sure that everyone gets
   > the same CPU. You can change partition/account/time needed (`-t`).

   Targets:
  
   |Problem|GFLOPS|
   |-------|------|
   |1      |     2|
   |2      |     2|
   |3      |     5|

   You can aim for even higher GFLOPs.<br/>
   See: https://piazza.com/class/ke8r6v61593760?cid=116 if you are confused about the workflow.
# Submission
  Put your report in PDF format (report.pdf) in Prog-assignment1 folder and create zip file of
  Prog-assignment1 folder and upload it to canvas.

# Notes
   1. If you use code hosting website including chpc's gitlab make sure you
      create private repository.
   2. If you have questions, ask on Piazza under `Prog-assignment1`.
   3. See [chpc_guide.docx](https://utah.instructure.com/courses/638169/files/folder/Notes-Handouts?preview=105874702) if you haven't already.


## Other

To see other attempts at optimization (that weren't as good), see commit aefd506a5e7638317df2e6176d561d39beffc024
