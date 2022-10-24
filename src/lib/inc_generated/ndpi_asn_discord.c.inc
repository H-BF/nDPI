/*
 *
 * This file is generated automatically and part of nDPI
 *
 * nDPI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * nDPI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with nDPI.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* ****************************************************** */


#if 0
static ndpi_network ndpi_protocol_discord_protocol_list[] = {
 { 0x05C80000 /* 5.200.0.0/19 */, 19, NDPI_PROTOCOL_DISCORD },
 { 0x1FCC8000 /* 31.204.128.0/19 */, 19, NDPI_PROTOCOL_DISCORD },
 { 0x2BEF8800 /* 43.239.136.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0x2D53C800 /* 45.83.200.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0x2D7C8400 /* 45.124.132.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0x4216C400 /* 66.22.196.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0x4216C800 /* 66.22.200.0/21 */, 21, NDPI_PROTOCOL_DISCORD },
 { 0x4216D000 /* 66.22.208.0/20 */, 20, NDPI_PROTOCOL_DISCORD },
 { 0x4216E000 /* 66.22.224.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0x4216E600 /* 66.22.230.0/23 */, 23, NDPI_PROTOCOL_DISCORD },
 { 0x4216E800 /* 66.22.232.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0x4216EC00 /* 66.22.236.0/23 */, 23, NDPI_PROTOCOL_DISCORD },
 { 0x4216EE00 /* 66.22.238.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0x4216F000 /* 66.22.240.0/23 */, 23, NDPI_PROTOCOL_DISCORD },
 { 0x4216F200 /* 66.22.242.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0x4216F400 /* 66.22.244.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0x4216F800 /* 66.22.248.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0x45A8EA00 /* 69.168.234.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0x559F7200 /* 85.159.114.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0x5968A000 /* 89.104.160.0/21 */, 21, NDPI_PROTOCOL_DISCORD },
 { 0x5BC3EA00 /* 91.195.234.0/23 */, 23, NDPI_PROTOCOL_DISCORD },
 { 0x5BC69800 /* 91.198.152.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0x5BD8CF00 /* 91.216.207.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0x677DD800 /* 103.125.216.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0x677DDB00 /* 103.125.219.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0x679F7A00 /* 103.159.122.0/23 */, 23, NDPI_PROTOCOL_DISCORD },
 { 0x67C2A400 /* 103.194.164.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0x68995400 /* 104.153.84.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0x6DC8C000 /* 109.200.192.0/19 */, 19, NDPI_PROTOCOL_DISCORD },
 { 0x8A808800 /* 138.128.136.0/21 */, 21, NDPI_PROTOCOL_DISCORD },
 { 0x92F74C00 /* 146.247.76.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xA2F43400 /* 162.244.52.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xA2F5CC00 /* 162.245.204.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB2F89B00 /* 178.248.155.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xB9298C00 /* 185.41.140.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9326800 /* 185.50.104.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9340C00 /* 185.52.12.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9462F00 /* 185.70.47.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xB94DD000 /* 185.77.208.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9729C00 /* 185.114.156.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9782300 /* 185.120.35.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xB9A23800 /* 185.162.56.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9A53000 /* 185.165.48.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xB9ABF000 /* 185.171.240.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9AC8400 /* 185.172.132.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9B3C800 /* 185.179.200.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9B9D400 /* 185.185.212.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9BDB400 /* 185.189.180.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9BFF000 /* 185.191.240.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9C51800 /* 185.197.24.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9C91100 /* 185.201.17.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xB9DAA400 /* 185.218.164.0/23 */, 23, NDPI_PROTOCOL_DISCORD },
 { 0xB9DAA600 /* 185.218.166.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xB9E28A00 /* 185.226.138.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xB9E52000 /* 185.229.32.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xB9F1D100 /* 185.241.209.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xBC7A4000 /* 188.122.64.0/19 */, 19, NDPI_PROTOCOL_DISCORD },
 { 0xC12BDA00 /* 193.43.218.0/23 */, 23, NDPI_PROTOCOL_DISCORD },
 { 0xC12E5000 /* 193.46.80.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xC23D3B00 /* 194.61.59.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xC71BD400 /* 199.27.212.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 { 0xCB841800 /* 203.132.24.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xD412E600 /* 212.18.230.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xD468C800 /* 212.104.200.0/23 */, 23, NDPI_PROTOCOL_DISCORD },
 { 0xD468CA00 /* 212.104.202.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xD468CD00 /* 212.104.205.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xD5A34000 /* 213.163.64.0/19 */, 19, NDPI_PROTOCOL_DISCORD },
 { 0xD5B3C000 /* 213.179.192.0/19 */, 19, NDPI_PROTOCOL_DISCORD },
 { 0xD5BE1600 /* 213.190.22.0/24 */, 24, NDPI_PROTOCOL_DISCORD },
 { 0xDC9ED800 /* 220.158.216.0/22 */, 22, NDPI_PROTOCOL_DISCORD },
 /* End */
 { 0x0, 0, 0 }
};
#endif