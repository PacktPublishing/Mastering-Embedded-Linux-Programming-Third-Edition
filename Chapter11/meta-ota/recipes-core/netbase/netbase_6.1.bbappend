do_install_append () { 
	echo "10.0.2.2 docker.mender.io s3.docker.mender.io" >> ${D}${sysconfdir}/hosts 
}
