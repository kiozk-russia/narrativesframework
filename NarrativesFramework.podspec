Pod::Spec.new do |s|

    s.name = 'NarrativesFramework'
    s.version = '2.4.3'
    s.platform = :ios, '9.0'
    s.license  = { :type => 'MIT', :file => 'LICENSE' }
    s.homepage = 'https://git.kiozk.ru/public-projects/narrativesframework'
    s.author = { "St.Pashik" => "stpashik@gmail.com" }
    s.source = { :git => 'https://git.kiozk.ru/public-projects/narrativesframework.git', :tag => s.version }
    s.summary = 'Библиотека для представления нарративов (Stories) с возможностью кастомизации.'
    s.description = 'Библиотека для представления нарративов (Stories) с возможностью кастомизации предоставляемая для работы с сайтом Narrator' \
                    'You can customize every detail. Make Stories of your dream! :)'

    s.vendored_frameworks = "NarrativesFramework.framework"
    #s.public_header_files = "NarrativesFramework.framework/Headers/*.h"
end