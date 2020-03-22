PROTODIR = $(PWD)
GENOUTDIR = $(PWD)/Gen
PROTOFILES = $(PROTODIR)/messages.proto

all:
	protoc --plugin=protoc-gen-nanopb=nanopb/generator/protoc-gen-nanopb \
	--proto_path=$(PWD) \
	--nanopb_out=$(GENOUTDIR) $(PROTOFILES)