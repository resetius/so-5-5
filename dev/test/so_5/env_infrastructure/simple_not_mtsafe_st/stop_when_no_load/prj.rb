require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	required_prj 'so_5/prj.rb'

	target '_unit.test.env_infrastructure.simple_not_mtsafe_st.stop_when_no_load'

	cpp_source 'main.cpp'
}

