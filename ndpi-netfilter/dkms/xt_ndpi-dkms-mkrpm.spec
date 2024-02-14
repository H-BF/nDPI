%{?!module_name: %{error: You did not specify a module name (%%module_name)}}
%{?!version: %{error: You did not specify a module version (%%version)}}
%{?!kernel_versions: %{error: You did not specify kernel versions (%%kernel_version)}}
%{?!packager: %define packager DKMS <dkms-devel@lists.us.dell.com>}
%{?!license: %define license Unknown}
%{?!_dkmsdir: %define _dkmsdir /var/lib/dkms}
%{?!_srcdir: %define _srcdir %_prefix/src}
%{?!_datarootdir: %define _datarootdir %{_datadir}}

Summary: ndpi Kernel Module
Name: %{module_name}
Version: %{version}
Release: 0
License: %license
Group: System/Kernel
#URL:
Source: %{module_name}-%{version}.dkms.tar.gz
BuildRoot: %{_tmppath}/%{module_name}-%{version}
BuildArch: noarch
Requires: gcc, make
Requires(post): dkms
Requires(preun): dkms

%description
This is ndpi kernel module.

echo -e "START BUILD"

%prep
if [ "%mktarball_line" != "none" ]; then
        /usr/sbin/dkms mktarball -m %module_name -v %version %mktarball_line --archive `basename %{module_name}-%{version}.dkms.tar.gz`
        cp -af %{_dkmsdir}/%{module_name}/%{version}/tarball/`basename %{module_name}-%{version}.dkms.tar.gz` %{module_name}-%{version}.dkms.tar.gz
fi
#%setup -n %{module_name}-%{version}

#%build

%install
if [ "$RPM_BUILD_ROOT" != "/" ]; then
        rm -rf $RPM_BUILD_ROOT
fi
mkdir -p $RPM_BUILD_ROOT/%{_srcdir}
mkdir -p $RPM_BUILD_ROOT/%{_datarootdir}/%{module_name}

if [ -d %{_sourcedir}/%{module_name}-%{version} ]; then
        cp -Lpr %{_sourcedir}/%{module_name}-%{version} $RPM_BUILD_ROOT/%{_srcdir}
fi

if [ -f %{module_name}-%{version}.dkms.tar.gz ]; then
        install -m 644 %{module_name}-%{version}.dkms.tar.gz $RPM_BUILD_ROOT/%{_datarootdir}/%{module_name}
        install -m 644 %{module_name}-%{version}.dkms.tar.gz %{_sourcedir}/
fi

if [ -f %{_sourcedir}/common.postinst ]; then
        install -m 755 %{_sourcedir}/common.postinst $RPM_BUILD_ROOT/%{_datarootdir}/%{module_name}/postinst
fi

%define dkms_name %{module_name}
%define dkms_vers %{version}
%define quiet -q

# Kernel module sources install for dkms
#%{__mkdir_p} %{buildroot}%{_usrsrc}/%{dkms_name}-%{dkms_vers}/
#%{__cp} -a * %{buildroot}%{_usrsrc}/%{dkms_name}-%{dkms_vers}/

# Configuration for dkms
#%{__cat} > %{buildroot}%{_usrsrc}/%{dkms_name}-%{dkms_vers}/dkms.conf << 'EOF'
#PACKAGE_NAME=%{dkms_name}
#PACKAGE_VERSION=%{dkms_vers}
#BUILT_MODULE[0]="xt_ndpi"
#BUILT_MODULE_NAME[0]="xt_ndpi"
#DEST_MODULE_LOCATION[0]="/extra"
##REMAKE_INITRD="no"
#AUTOINSTALL="YES"
##POST_INSTALL="hdj_mod_post_install"
##POST_REMOVE="hdj_mod_post_remove"
#EOF
#

%clean
%{__rm} -rf %{buildroot}

%post
# Add to DKMS registry
dkms add -m %{dkms_name} -v %{dkms_vers} %{?quiet} || :
# Rebuild and make available for the currenty running kernel
dkms build -m %{dkms_name} -v %{dkms_vers} %{?quiet} || :
dkms install -m %{dkms_name} -v %{dkms_vers} %{?quiet} --force || :

%preun
# Remove all versions from DKMS registry
dkms remove -m %{dkms_name} -v %{dkms_vers} %{?quiet} --all || --rpm_safe_upgrade
exit 0

%files
%defattr(-, root, root, 0755)
%{_srcdir}
%{_datarootdir}/%{module_name}/
%{_usrsrc}/%{dkms_name}-%{dkms_vers}/


%changelog
* %(date "+%a %b %d %Y") %packager %{version}-%{release}
- Automatic build by DKMS