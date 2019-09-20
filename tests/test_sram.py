from cffi import FFI
import unittest

ffi = FFI()
with open("output/x86/sram.e") as f:
    ffi.cdef(f.read())
lib = ffi.dlopen("output/x86/sram.so")

class TestSRAM(unittest.TestCase):
    def test_check_sram_request_ok(self):
        result = lib.check_sram_request(0x0000, 0xFF)
        self.assertEqual(result, 0) # OK == 1

    def test_check_sram_request_OK_max(self):
        result = lib.check_sram_request(0x0000, 128*1024*2-1)
        self.assertEqual(result, 0)  # OK == 1

    def test_check_sram_request_KO(self):
        result = lib.check_sram_request(0x0000, 128*1024*2+1)
        self.assertEqual(result, 2)  # OORAM == 2

    def test_select_bank_sram_no_bank(self):
        result = lib.select_bank_sram(0x0001, 128*1024*2)
        NO_BANK = 0
        self.assertEqual(result, NO_BANK)

    def test_select_bank_sram_bank_0(self):
        result = lib.select_bank_sram(0x0000, 128)
        BANK_0 = 1
        self.assertEqual(result, BANK_0)

    def test_select_bank_sram_bank_1(self):
        result = lib.select_bank_sram(0x20001, 128)
        BANK_1 = 2
        self.assertEqual(result, BANK_1)

    def test_select_bank_sram_bank_0_1(self):
        result = lib.select_bank_sram(0x1FFFF, 128)
        BANK_0_AND_1 = 3
        self.assertEqual(result, BANK_0_AND_1)

    def split_sram_request(self, address, size):
        b0_addr = ffi.new("uint32_t *")
        b0_size = ffi.new("uint32_t *")
        b1_addr = ffi.new("uint32_t *")
        b1_size = ffi.new("uint32_t *")
        lib.split_sram_request(address, size, b0_addr,
                               b0_size, b1_addr, b1_size)
        return b0_addr[0], b0_size[0], b1_addr[0], b1_size[0]

    def test_split_sram_request_b0_addr(self):
        b0_addr, _, _, _ = self.split_sram_request(0x1FFF0, 128)
        self.assertEqual(b0_addr, 0x1FFF0)

    def test_split_sram_request_b0_size(self):
        _, b0_size, _, _ = self.split_sram_request(0x1FFF0, 128)
        self.assertEqual(b0_size, 0xF)

    def test_split_sram_request_b1_addr(self):
        _, _, b1_addr, _ = self.split_sram_request(0x1FFF0, 128)
        self.assertEqual(b1_addr, 0x00)

    def test_split_sram_request_b1_size(self):
        _, _, _, b1_size = self.split_sram_request(0x1FFF0, 128)
        self.assertEqual(b1_size, 128-0xF)

    def test_address_to_array(self):
        address_array = ffi.new("uint8_t[3]")
        lib.address_to_array(0x1FFF0, address_array)
        result = (address_array[0], address_array[1], address_array[2])
        self.assertEqual((1, 0xFF, 0xF0), result)

    


if __name__ == "__main__":
    unittest.main()
