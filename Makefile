all:
	jbuilder build @runlc;
	jbuilder build @runcw

clean:
	git clean -fdx

lint:
	ocp-indent -i */*.ml*
