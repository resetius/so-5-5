require 'mxx_ru/binary_unittest'

Mxx_ru::setup_target(
	Mxx_ru::Binary_unittest_target.new(
		"test/so_5/svc/svc_handler_exception/prj.ut.rb",
		"test/so_5/svc/svc_handler_exception/prj.rb" )
)
