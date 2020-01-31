Pod::Spec.new do |s|

    s.name = 'NarrativesFramework'
    s.version = '2.4.5'
    s.platform = :ios, '9.0'
    s.license  = { :type => 'MIT', :file => 'LICENSE' }
    s.homepage = 'https://github.com/kiozk-russia/narrativesframework'
    s.author = { "St.Pashik" => "stpashik@gmail.com" }
    s.source = { :git => 'https://github.com/kiozk-russia/narrativesframework', :tag => s.version }
    s.summary = 'Библиотека для представления нарративов (Stories) с возможностью кастомизации.'
    s.description = 'Библиотека для представления нарративов (Stories) с возможностью кастомизации предоставляемая для работы с сайтом Narrator' \
                    'You can customize every detail. Make Stories of your dream! :)'

    s.vendored_frameworks = "NarrativesFramework.framework"
    #s.public_header_files = "NarrativesFramework.framework/Headers/*.h"
end