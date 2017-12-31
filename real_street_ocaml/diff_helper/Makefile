all:
	jbuilder build @runtest-parser

clean:
	find . -name "*.swp" -exec rm -rf {} \;
	find . -name ".merlin" -exec rm -rf {} \;
	rm -rf _build

indent:
	find . -name "*.ml" -exec ocp-indent -i {} \;
