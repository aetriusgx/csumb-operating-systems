# Register all subdirectories in the project's root directory.
SUBDIRS :=  1-freesize  2-count_allocs  3-num_bytes  4-succ_reqs  5-list_sizes

test:
	for dir in $(SUBDIRS); do \
		$(MAKE) -i --no-print-directory -s -C $$dir test; \
	done

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -i --no-print-directory -C $$dir clean; \
	done