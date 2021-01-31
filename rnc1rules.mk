# Compress binary file
$(BUILD_DIR)/%.szp: $(BUILD_DIR)/%.bin
	$(call print,Compressing:,$<,$@)
	$(V)$(RNCPACK) p $< $@ -m1

# convert binary szp to object file
$(BUILD_DIR)/%.szp.o: $(BUILD_DIR)/%.szp
	$(call print,Converting RNC1 to ELF:,$<,$@)
	$(V)printf ".section .data\n\n.incbin \"$<\"\n" | $(AS) $(ASFLAGS) -o $@