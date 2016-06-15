# domain2host
domain2host is a simple CLI program written to add custom hostfile rules to a list of domains

## Usage
If you want to redirect domains in 'inputfile' to localhost (127.0.0.1), than you add a zero as argument:

`domain2host.exe 0 outputFile inputFile`

supports multiple files to read from (including exported firefox bookmarks), and custom domain to redirect to, example:

`domain2host.exe github.com outputFile inputFile1 inputFile2`

`domain2host.exe example.com newHostsFile.txt someListOfDomains.txt bookmarks.html`

It checks for double domains and if a domain has already ben added, it skips it.

###TO DO:
-make it possible to read from a file where domains are not separated in lines but with commas (or anything similar)
-append to current host file 

###DONE:
-read from a exported bookmark file and create new host file with that
