RED='\e[0;31m'
NC='\e[0m'                      # No Color

cd ~

echo -e "${RED}This is current directory:${NC}"
ls

echo -e "${RED}Entering code directory using pushd:${NC}"
pushd code

echo -e "${RED}This is code directory:${NC}"
ls

echo -e "${RED}Return to previous directory using popd:${NC}"
popd
