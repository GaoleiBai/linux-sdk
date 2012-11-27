.PHONY: clean All

All:
	@echo ----------Building project:[ SDKLinux - Debug ]----------
	@"$(MAKE)" -f "SDKLinux.mk"
clean:
	@echo ----------Cleaning project:[ SDKLinux - Debug ]----------
	@"$(MAKE)" -f "SDKLinux.mk" clean
