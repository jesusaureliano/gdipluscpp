.PHONY: clean All

All:
	@echo "----------Building project:[ DrawPath - Debug ]----------"
	@cd "DrawPath" && "$(MAKE)" -f  "DrawPath.mk"
clean:
	@echo "----------Cleaning project:[ DrawPath - Debug ]----------"
	@cd "DrawPath" && "$(MAKE)" -f  "DrawPath.mk" clean
